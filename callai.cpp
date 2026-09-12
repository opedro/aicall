#include <iostream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

extern "C" {
	#include <flite/flite.h>
}

extern "C" cst_voice *register_cmu_us_kal(const char *voxdir);

void out(string texto_saida, int com_fala=0){
	cout << texto_saida << endl;
	if(com_fala){
		flite_init();
		cst_voice *voice = register_cmu_us_kal(NULL);
		flite_text_to_speech(texto_saida.c_str(), voice, "play");
	}
	return;
}

void callAPIClima(httplib::Headers headers, int fala=0){
	httplib::Client cli("https://api.open-meteo.com");

	if (auto res = cli.Get("/v1/forecast?latitude=-23.638474&longitude=-46.736305&current=temperature_2m", headers)){
		if (res->status == 200) {
			try {
				json data = json::parse(res->body);
				string temperatura = data["current"]["temperature_2m"].dump();
				temperatura.append(" ºC");
				out(temperatura, fala);
			}catch (json::parse_error& e){
				cout << "Erro ao parsear JSON: " << e.what() << endl;
			}
		}else{
			cout << "Erro HTTP: " << res->status << endl;
		}
	} else {
		auto err = res.error();
		cout << "Erro na conexao: " << httplib::to_string(err) << endl; 
	}
}

void callAPIPiada(httplib::Headers headers, int fala = 0){
	httplib::Client cli("https://official-joke-api.appspot.com");
	
	if (auto res = cli.Get("/random_joke", headers)){
		if (res->status == 200){
			try {
				json data = json::parse(res->body);
				string setup = data["setup"];
				string punchline = data["punchline"];
				out(setup, fala);
				cin.get();
				out(punchline, fala);
				
			}catch(json::parse_error & e){
				cout << "Erro ao parsear JSON: " << e.what() << endl;				
			} 
		} else {
			cout << "Erro na API " << endl;
		}
	}
}

void callAPIGemini(int fala = 0){
	string api_key = "APIKEY AQUI";
	string text_prompt;
	out("Como posso te ajudar", fala);
	getline(cin, text_prompt);

	json request_body = {
		{"contents", json::array({
			{{"parts", json::array({{{"text", text_prompt}}})}}
		})}
	};

	httplib::Client cli("https://generativelanguage.googleapis.com");
	cli.set_read_timeout(30,0);
	httplib::Headers headers = {{"Content-type", "application/json"}};
	string path = "/v1beta/models/gemini-3.5-flash-lite:generateContent?key=" + api_key;

	auto res = cli.Post(path.c_str(), headers, request_body.dump(), "application/json");

	if(res){
		if(res->status == 200){
			try{
				json response_json = json::parse(res->body);

				string gemini_response = response_json["candidates"][0]["content"]["parts"][0]["text"];
				out(gemini_response, fala);
			}catch(json::exception & e){
				cerr << "Erro ao ler o JSON " << e.what() << endl;
			}
		}else{
			cerr << "Erro HTTP: " << res->status << "\nDetalhes: " << res->body << endl;	
		}
	} else {
		cerr << "Falha ao fazer a request" << endl;
	}
}

int main(int argc, char* argv[]){
	if (argc < 2){
		cerr << "Uso: " << argv[0] << " <clima|piada|etc> " << endl;
		return 1;
	}
	string opcao;
	int fala = 0;
	
	for (int i = 0; i < argc; i++){
		string arg = argv[i];
		if (arg == "clima" || arg == "1"){
			opcao = arg;
			continue;
		}
		if (arg == "piada" || arg == "2"){
			opcao = arg;
			continue;
		}
		if (arg == "gemini" || arg == "3"){
			opcao = arg;
			continue;
		}
		if (arg == "-f"){
			fala = 1;
			continue;
		}
	}
	

	//Setup dos headers
	httplib::Headers headers = {
		{"User-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"},
		{"Accept", "application/json"}
	};


	if (opcao == "clima" || opcao == "1") {
		callAPIClima(headers, fala);
		return 0;
	} else if (opcao == "piada" || opcao == "2") {
		callAPIPiada(headers, fala);
		return 0;
	} else if (opcao == "gemini" || opcao == "3"){
		callAPIGemini(fala);
	} 
	else {
		cout << "Opcoes disponiveis:" << endl;
		cout << "1 - clima" << endl;
		cout << "2 - piada" << endl;
		cout << "3 - gemini" << endl;

		return 1;
	}
	
}
