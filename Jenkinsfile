pipeline {
    agent { dockerfile true }
    stages {
        stage ("Test") {
            steps {
                sh "g++ --version"
                sh "cmake --version"
            }
        }
    }

}