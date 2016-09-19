FROM absalomedia/mini
MAINTAINER Lawrence Meckan <media@absalom.biz>

# Set correct environment variables.
ENV DOCKER_NAME rev_tensile
ENV DEBIAN_FRONTEND noninteractive
ENV HOME /root
ENV DEFAULT_TIMEZONE Australia/Brisbane

# Enable ssh access
RUN rm -f /etc/service/sshd/down

# Regenerate SSH host keys. baseimage-docker does not contain any, so you
# have to do that yourself. You may also comment out this instruction; the
# init system will auto-generate one during boot.
# RUN /etc/my_init.d/00_regen_ssh_host_keys.sh

# !!! Enabling the insecure key permanently !!! REMOVE ME AT PRODUCTION
# RUN /usr/sbin/enable_insecure_key

# Use baseimage-docker's init system.
CMD ["/sbin/my_init"]

RUN apt-get update \
  && apt-get -y install wget curl python-software-properties curl unzip git build-essential clang-3.6 pkg-config zip zlib1g-dev default-jdk \
  && apt-get -y upgrade \
  && apt-get -y clean \
  && rm -rf /tmp/* /var/tmp/*

RUN apt-get update && \
    curl https://get.docker.com/builds/Linux/x86_64/docker-1.9.1 > /usr/bin/docker && chmod +x /usr/bin/docker && \

    # This makes add-apt-repository available.
    apt-get -y install software-properties-common && \

    add-apt-repository ppa:webupd8team/java && \
    apt-get update && \

    # Accept the installer license && \
    echo "oracle-java7-installer shared/accepted-oracle-license-v1-1 boolean true" && \
    echo debconf shared/accepted-oracle-license-v1-1 select true | debconf-set-selections && \

    apt-get -y install oracle-java8-installer && \
    echo "deb http://storage.googleapis.com/bazel-apt stable jdk1.8" | tee /etc/apt/sources.list.d/bazel.list && \
    apt-get -y install curl && \
    curl https://storage.googleapis.com/bazel-apt/doc/apt-key.pub.gpg | apt-key add - && \
    apt-get update && \

    apt-get -y install bazel && \
    apt-get upgrade bazel && \
    apt-get install python-numpy swig python-dev python-wheel && \
    # Unpack bazel for future use.
    bazel version

ENTRYPOINT ["bazel"]

WORKDIR /usr/src

RUN git clone https://github.com/absalomedia/tensile.git && \
  cd tensile && \
  git submodule update --init --recursive && \
  cd lib/tensorflow/tensorflow && \
  bazel build --genrule_strategy=standalone --spawn_strategy=standalone //tensorflow:libtensorflow.so
