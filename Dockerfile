FROM alpine:3.21

ENV CALLAI_AUDIO=0

WORKDIR /app
COPY dependencies.sh callai.cpp httplib.h ./

RUN sed -i 's/\r$//' dependencies.sh \
        && chmod +x dependencies.sh \
        && sh ./dependencies.sh

RUN g++ callai.cpp -o callAI \
        -lssl \
        -lcrypto \
        -lflite \
        -lflite_cmu_us_kal \
        -lm

ENTRYPOINT ["/app/callAI"]
