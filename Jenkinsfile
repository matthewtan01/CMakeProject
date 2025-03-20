pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile.agent.linux'
        }
    }
    stages {
        stage('Build') {
            steps {
               sh 'echo "Running inside windows container"'
            }
        }
    }
}
