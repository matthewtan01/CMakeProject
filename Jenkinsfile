pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile'
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
