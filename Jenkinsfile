pipeline {
    agent {
        dockerfile {
            filename 'Dockerfile'
            args '-v /c/Users/tyonghan/AppData/Local/Jenkins/.jenkins/workspace/docker_cmake:/workspace'
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
