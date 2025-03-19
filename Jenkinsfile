pipeline {
    agent {
        docker {
            image 'ubuntu:22.04'
            args '--mount type=volume,src=jenkins-workspace,dst=/workspace'
        }
    }
    stages {
        stage('Build') {
            steps {
                sh 'echo "Building in Linux container with proper workspace"'
            }
        }
    }
}
