from debian:9

run apt-get update && \
    apt-get install -y cmake g++ gcc build-essential librpmbuild3 \
                       libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev \
                       libsdl2-ttf-dev

run apt-get install -y rpm

run mkdir -p /game/build/game /game/code /game/packs

add . /game/code

cmd cd /game/build/game && cmake -DRELEASE_BUILD=ON /game/code && make                 && \
    cpack --config CPackConfig.cmake -G DEB -D CPACK_DEBIAN_PACKAGE_ARCHITECTURE=i386  && \
    cpack --config CPackConfig.cmake -G DEB -D CPACK_DEBIAN_PACKAGE_ARCHITECTURE=amd64 && \
    cpack --config CPackConfig.cmake -G RPM -D CPACK_RPM_PACKAGE_ARCHITECTURE=i386     && \
    cpack --config CPackConfig.cmake -G RPM -D CPACK_RPM_PACKAGE_ARCHITECTURE=x86_64   && \
    cp *.rpm *.deb /game/packs
