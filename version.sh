# Tensorflow versions
TF_TYPE=cpu
TF_VERSION=1.12.0
# Prep for build sequence
sudo wget -qO - https://storage.googleapis.com/tensorflow/libtensorflow/libtensorflow-${TF_TYPE}-linux-x86_64-${TF_VERSION}.tar.gz  | tar zxf - -C .