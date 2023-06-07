FROM qmkfm/qmk_cli

MAINTAINER knirch

RUN apt update
RUN apt-get upgrade -y
RUN apt-get install -y git vim

RUN addgroup --gid 1000 user
RUN adduser user --home /home/user --uid 1000 --gid 1000

RUN apt-get install ccache

USER 1000

VOLUME /home/user/.config/qmk

VOLUME /qmk_firmware
WORKDIR /qmk_firmware

CMD /bin/bash
