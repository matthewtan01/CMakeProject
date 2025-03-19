pipeline {
    agent {
        docker {
            image 'ubuntu:22.04'
            args '--workdir /workspace -v /workspace:/workspace' // Override Windows path
        }
    }
    environment {
        WORKSPACE_PATH = sh(script: 'pwd', returnStdout: true).trim()  // Ensure Unix path
    }
    stages {
        stage("Test") {
            steps {
                sh 'echo "Current directory: ${env.WORKSPACE_PATH}"'
                sh 'g++ --version'
                sh 'cmake --version'
            }
        }
    }
}
