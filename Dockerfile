FROM absalomedia/bazel
MAINTAINER Lawrence Meckan <media@absalom.biz>

# Set correct environment variables.
ENV DOCKER_NAME rev_tensile
ENV DEBIAN_FRONTEND noninteractive
ENV HOME /root
ENV DEFAULT_TIMEZONE Australia/Brisbane

# Tensorflow shared object
ENV TF_TYPE=cpu
ENV TF_OS=linux

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

WORKDIR /usr/src

RUN git clone https://github.com/absalomedia/tensile.git && \
  cd tensile 
RUN ./configure
RUN bazel build -c opt tensorflow:libtensorflow.so
