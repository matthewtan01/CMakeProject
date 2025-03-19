pipeline {
    agent {
        docker {
            image 'ubuntu:22.04'
            args "-v ${env.WORKSPACE}:/workspace --workdir /workspace" // Ensure Jenkins maps workspace correctly
        }
    }
    environment {
        WORKSPACE_PATH = "/workspace"  // Ensure the path is correct inside the container
    }

    stages {
        stage("Test") {
            steps {
                sh 'echo "Current directory: ${WORKSPACE_PATH}"'
                sh 'g++ --version'
                sh 'cmake --version'
            }
        }
    }
}
