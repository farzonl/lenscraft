DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

UNAME="$(uname)"
glfwVersion=$(pkg-config libglfw --modversion )
if [[ -z "$glfwVersion" ]]; then
    # Unzip the dependency
    if [ ! -d "$DIR/glfw-2.7.9" ]; then
        unzip "$DIR/glfw-2.7.9.zip" -d $DIR
    fi

    # Build the dependency
    if [ "$UNAME" = "Darwin" ]; then
        make -C glfw-2.7.9 cocoa
        sudo make -C glfw-2.7.9 cocoa-install 
    fi
    if [ "$UNAME" = "Linux" ]; then 
        make -C glfw-2.7.9 x11
        sudo make -C glfw-2.7.9 x11-install
    fi
fi

glmVersion=$(pkg-config glm --modversion )
if [[ -z "$glmVersion" ]]; then
    glmVersion=$(whereis glm )
fi

if [[ -z "$glmVersion" ]]; then
    # fetch the dependency
    if [ ! -f "$DIR/glm-0.9.9.5.zip" ]; then
        wget "https://github.com/g-truc/glm/releases/download/0.9.9.5/glm-0.9.9.5.zip"
    fi

    # Unzip the dependency
    if [ ! -d "$DIR/glm" ]; then
        unzip "$DIR/glm-0.9.9.5.zip" -d $DIR
        mkdir "$DIR/glm/release"
    fi

    # Build the dependency
    pushd "$DIR/glm/release"
    cmake ../
    make all -j$(nproc)
    sudo make install
    popd
fi

# building opencv2 from scratch on mac takes too much
# time,lets only build it for linux if we have too.
if [ "$UNAME" = "Linux" ]; then
    opencvVersion=$(pkg-config opencv --modversion )
    badversion="3.0.0"
    if [ "$(printf '%s\n' "$badversion" "$opencvVersion" | sort -V | head -n1)" = "$badversion" ]; then
        echo "version of Opencv installed: ($opencvVersion) is too new, unistalling!"
        sudo apt-get remove libopencv-dev
        opencvVersion=$(pkg-config opencv --modversion )
    fi
    if [[ -z "$opencvVersion" ]]; then
        opencv="opencv-2.4.13.5"
        # fetch the dependency
        if [ ! -f "$DIR/$opencv.zip" ]; then
            wget "https://github.com/opencv/opencv/archive/2.4.13.5.zip" -O "$opencv.zip"
        fi
        # Unzip the dependency
        if [ ! -d "$DIR/$opencv" ]; then
            unzip "$opencv.zip" -d $DIR
            mkdir "$DIR/$opencv/release"
        fi
        # Build the dependency
        pushd "$DIR/$opencv/release"
        cmake -G "Unix Makefiles" -DCMAKE_CXX_COMPILER=/usr/bin/g++ CMAKE_C_COMPILER=/usr/bin/gcc -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=/usr/local -DWITH_FFMPEG=OFF -DWITH_JPEG=OFF -DWITH_PNG=OFF -DWITH_TIFF=OFF -DWITH_TBB=ON -DWITH_OPENGL=ON -DINSTALL_TO_MANGLED_PATHS=ON -DINSTALL_CREATE_DISTRIB=ON -DENABLE_FAST_MATH=ON -DWITH_IMAGEIO=ON -DBUILD_SHARED_LIBS=OFF -DWITH_GSTREAMER=ON ..
        make all -j$(nproc) # Uses all machine cores
        sudo make install
        popd
    fi
fi