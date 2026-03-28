FROM gcc:latest
WORKDIR /app
COPY ./src /app/src
COPY ./Makefile /app/
RUN make all
CMD ["/app/run_c.sh"]
