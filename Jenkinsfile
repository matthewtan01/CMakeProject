pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile'  // Ensure your Dockerfile exists in the workspace
            additionalBuildArgs '--no-cache'  // Optional: Forces a fresh build
        }
    }
    stages {
        stage('Build') {
            steps {
                sh 'pwd'
                sh 'echo "Running inside container"'
            }
        }
    }
}
