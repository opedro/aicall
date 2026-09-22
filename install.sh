source ./compile.sh
cp ./callAI /usr/local/bin/AI
export AI_API_KEYS=$(cat ./api_key.json)
