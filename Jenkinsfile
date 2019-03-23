pipeline {
  agent any
  stages {
    stage('build g++') {
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

    stage('test g++') {
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

    stage('build clang++') {
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

    stage('test clang++') {
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
    }  }
}
