pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile.agent.linux'
        }
    }
    stages {
        stage('Build') {
            steps {
                sh '''
                    g++ --version
                    cmake --version
                    mkdir -p build
                    cd build
                    cmake ..
                    cmake --build .
                '''
            }
        }

        stage('Test') {
            steps { 
                sh '''
                    cd build/test_project
                    ctest --output-on-failure
                '''
            }
        }
    }
}
