pipeline {
    agent { dockerfile true }
    environment {
        WORKSPACE_PATH = sh(script: 'pwd', returnStdout: true).trim() // Get Unix path
    }
    stages {
        stage("Test") {
            steps {
                sh "echo \"Current directory: ${env.WORKSPACE_PATH}\"" // Fix variable expansion
                sh 'g++ --version'
                sh 'cmake --version'
            }
        }
    }
}
