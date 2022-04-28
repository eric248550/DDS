#FROM scratch
FROM ubuntu:16.04
#FROM gcc:latest
MAINTAINER Alvin <b10602126@gapps.ntust.edu.tw>

# USER root
# # 設定工作目錄為 /DDS
# WORKDIR /DDS
# # 複製目前目錄下的內容，放進 Docker 容器中的 /DDS
# ADD . /DDS

RUN apt-get update \
&& apt-get install -y make\
&& apt-get install -y cmake libssl-dev libsasl2-dev

COPY dispenser /home/dispenser
COPY rti_connext_dds-6.0.0 /home/rti_connext_dds-6.0.0
COPY starter.sh /home

RUN chmod +x /home/starter.sh
# ENV PATH $PATH:/DDS
# ENV PATH="/rti_connext_dds-6.0.0/bin:$PATH"
ENV HOME=/home
ENV NDDSHOME=$HOME/rti_connext_dds-6.0.0
ENV LD_LIBRARY_PATH=$NDDSHOME/lib/x64Linux3gcc5.4.0

# BOTH:
# ENV MODE
# ENV ROLE

# ONLY WHEN SUBSCRIBING:
# ENV MONGO_ADDRESS

# MODE LAN
# ENV PUB_PEER
# ENV PUB_BINDPORT
# ENV SUB_PEER
# ENV SUB_BINDPORT

# MODE WAN
# ENV PUB_PUBLICIP
# ENV PUB_BINDPORT
# ENV SUB_PEER

EXPOSE 7400

ENTRYPOINT ["./home/starter.sh"]

#CMD tail -f /dev/null