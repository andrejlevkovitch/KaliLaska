pipeline {
  stages {
    stage('build linux') {
      agent {
        docker {
          image 'andrejlevkovitch/xenial-sdl:latest'
        }
      }
      steps {
        sh 'rm -rf build'
        sh 'mkdir build'
        sh 'cd build && cmake ..'
        sh 'cmake --build build -- -j4'
      }
    }

    stage('test linux') {
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
  }
}
