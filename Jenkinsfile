pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile.agent.linux'
        }
    }
    stages {
        stage('Build') {
            steps {
               sh 'echo "Running inside linux container"'
               sh 'g++ --version'
               sh 'cmake --version'
            }
        }
    }
}
