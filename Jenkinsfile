pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile.agent.linux'
        }
    }
    stages {
        stage('Build') {
            steps {
                bat 'echo "Running inside windows container" '
            }
        }
    }
}
