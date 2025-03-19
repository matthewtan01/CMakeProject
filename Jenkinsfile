pipeline {
    agent { dockerfile true }
    environment {
        WORKSPACE_PATH = sh(script: 'pwd', returnStdout: true).trim() // Get the correct Unix path
    }
    stages {
        stage ("Test") {
            steps {
                sh 'echo "Current directory: $WORKSPACE_PATH"'
                sh "g++ --version"
                sh "cmake --version"
            }
        }
    }

}