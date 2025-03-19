pipeline {
    agent { dockerfile true }
    environment {
        // Convert Windows path to Unix path using cygpath
        WORKSPACE_PATH = sh(script: 'cygpath -u "$WORKSPACE"', returnStdout: true).trim()
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
