FROM alpine:latest

RUN apk add --no-cache gcc make musl-dev
WORKDIR /app
COPY ./src /app/src
COPY ./Makefile /app/
RUN make all
CMD ["/app/run_c.sh"]
