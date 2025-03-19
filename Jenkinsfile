pipeline {
    agent {
        docker {
            image 'ubuntu:22.04'
            args '--mount type=volume,src=jenkins-workspace,dst=/workspace'
            reuseNode true
        }
    }
    stages {
        stage('Build') {
            steps {
                ws('/workspace') {  // Force Jenkins to use /workspace
                    sh 'pwd'
                    sh 'echo "Running inside container"'
                }
            }
        }
    }
}
