FROM alpine:3.20

WORKDIR /app
COPY dependencies.sh callai.cpp httplib.h ./

RUN apk update && apk add --no-cache bash \
        && sed -i 's/\r$//' dependencies.sh \
        && chmod +x dependencies.sh \
        && sh ./dependencies.sh

RUN g++ callai.cpp -o callAI \
        -lssl \
        -lcrypto \
        -lflite \
        -lflite_cmu_us_kal \
        -lm

