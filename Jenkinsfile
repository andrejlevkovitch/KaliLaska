pipeline {
  agent any
  stages {
    stage('build gnu') {
      agent {
        docker {
          image 'andrejlevkovitch/xenial-sdl:latest'
        }
      }
      steps {
        sh 'rm -rf build'
        sh 'mkdir build'
        sh 'cd build && cmake -DCMAKE_CXX_COMPILER=g++ ..'
        sh 'cmake --build build'
      }
    }

    stage('test gnu') {
      agent {
        docker {
          image 'andrejlevkovitch/xenial-sdl:latest'
        }
      }
      steps {
        withEnv(['DISPLAY=:0']) {
          sh 'Xvfb :0 -fbdir /tmp &'
          sh 'cmake --build build --target test'
        }
      }
    }

    stage('build clang') {
      agent {
        docker {
          image 'andrejlevkovitch/xenial-sdl:latest'
        }
      }
      steps {
        sh 'rm -rf build'
        sh 'mkdir build'
        sh 'cd build && cmake -DCMAKE_CXX_COMPILER=clang++ ..'
        sh 'cmake --build build'
      }
    }

    stage('test clang') {
      agent {
        docker {
          image 'andrejlevkovitch/xenial-sdl:latest'
        }
      }
      steps {
        withEnv(['DISPLAY=:0']) {
          sh 'Xvfb :0 -fbdir /tmp &'
          sh 'cmake --build build --target test'
        }
      }
    }  

    stage('build mingw') {
      agent {
        docker {
          image 'andrejlevkovitch/mingw64sdl:latest'
        }
      }
      steps {
        sh 'rm -rf build'
        sh 'mkdir build'
        sh 'cd build && cmake ..'
        sh 'cmake --build build'
      }
    }

    stage('test mingw') {
      agent {
        docker {
          image 'andrejlevkovitch/mingw64sdl:latest'
        }
      }
      steps {
        withEnv(['DISPLAY=:0']) {
          sh 'Xvfb :0 -fbdir /tmp &'
          sh 'cmake --build build --target test'
        }
      }
    }  
  }
}
