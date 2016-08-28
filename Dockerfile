FROM absalomedia/mini
MAINTAINER Lawrence Meckan <media@absalom.biz>

# Set correct environment variables.
ENV DOCKER_NAME rev_tensile
ENV VER_BAZEL 0.3.1
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
  && apt-get -y install wget curl unzip git build-essential python-numpy swig python-dev clang-3.6 oracle-java8-installer pkg-config zip zlib1g-dev \
  && apt-get -y upgrade \
  && apt-get -y clean \
  && rm -rf /tmp/* /var/tmp/*

RUN echo "Downloading Bazel v${VER_BAZEL} ..." && wget -qO - https://github.com/bazelbuild/bazel/releases/download/${VER_BAZEL}/bazel-${VER_BAZEL}-jdk7-installer-linux-x86_64.sh -C /tmp
RUN echo "Setting up Bazel v${VER_BAZEL} ..." && sudo chmod +x /tmp/bazel-${VER_BAZEL}-jdk7-installer-linux-x86_64.sh
RUN echo "Running Bazel v${VER_BAZEL} installer..." && cd /tmp && ./bazel-${VER_BAZEL}-jdk7-installer-linux-x86_64.sh --user

WORKDIR /usr/src

RUN git clone https://github.com/absalomedia/tensile.git && \
  cd tensile && \
  git submodule update --init --recursive && \
  cd lib/tensorflow/tensorflow && \
  bazel build --genrule_strategy=standalone --spawn_strategy=standalone //tensorflow:libtensorflow.so
