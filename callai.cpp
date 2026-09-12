#include <iostream>
#include <fstream>
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

extern "C" {
	#include <flite/flite.h>
}

extern "C" cst_voice *register_cmu_us_kal(const char *voxdir);

void out(string texto_saida, int com_salva, int com_fala){
	cout << texto_saida << endl;

	if(com_salva){
		ofstream saidas("./saidas/saidas.txt", ios::app);
		saidas << endl << "====================================" << endl << texto_saida ;		
		saidas.close();
	}
	if(com_fala){
		flite_init();
		cst_voice *voice = register_cmu_us_kal(NULL);
		flite_text_to_speech(texto_saida.c_str(), voice, "play");
	}
	return;
}

void callAPIClima(httplib::Headers headers, int salva, int fala){
	httplib::Client cli("https://api.open-meteo.com");

	if (auto res = cli.Get("/v1/forecast?latitude=-23.638474&longitude=-46.736305&current=temperature_2m", headers)){
		if (res->status == 200) {
			try {
				json data = json::parse(res->body);
				string temperatura = data["current"]["temperature_2m"].dump();
				temperatura.append(" ºC");
				out(temperatura, salva, fala);
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

void callAPIPiada(httplib::Headers headers,int salva, int fala){
	httplib::Client cli("https://official-joke-api.appspot.com");
	
	if (auto res = cli.Get("/random_joke", headers)){
		if (res->status == 200){
			try {
				json data = json::parse(res->body);
				string setup = data["setup"];
				string punchline = data["punchline"];
				out(setup, salva, fala);
				cin.get();
				out(punchline, salva, fala);
				
			}catch(json::parse_error & e){
				cout << "Erro ao parsear JSON: " << e.what() << endl;				
			} 
		} else {
			cout << "Erro na API " << endl;
		}
	}
}

void callAPIGemini(int salva, int fala){
	ifstream arquivo_keys("api_key.json");
	if(!arquivo_keys.is_open()){
		cerr << "Erro ao ler keys, garanta que você criou seu arquivo de api_keys" << endl;
		return;
	}
	json keys;
	arquivo_keys >> keys;
	if(!keys.contains("gemini")){
		cerr << "Nao foi encontrada api_key do gemini no seu arquivo de api_keys, atualize seu arquivo para utilizar" << endl;
		return;
	}
	string api_key = keys["gemini"];
	
	string text_prompt;
	out("Como posso te ajudar?", salva, fala);

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
				out(gemini_response, salva, fala);
			}catch(json::exception & e){
				cerr << "Erro ao ler o JSON " << e.what() << endl;
			}
		} else if(res->status== 400){
			cerr << "Erro na chamada, verifique a sua api_key" << endl;
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
	int salva = 0;
	
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
		if (arg == "-s"){
			salva = 1;
			continue;
		}
	}
	

	//Setup dos headers
	httplib::Headers headers = {
		{"User-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64)"},
		{"Accept", "application/json"}
	};


	if (opcao == "clima" || opcao == "1") {
		callAPIClima(headers, salva, fala);
		return 0;
	} else if (opcao == "piada" || opcao == "2") {
		callAPIPiada(headers, salva, fala);
		return 0;
	} else if (opcao == "gemini" || opcao == "3"){
		callAPIGemini(salva, fala);
	} 
	else {
		cout << "Opcoes disponiveis:" << endl;
		cout << "1 - clima" << endl;
		cout << "2 - piada" << endl;
		cout << "3 - gemini" << endl;

		return 1;
	}
	
}
