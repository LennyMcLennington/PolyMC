pipeline {
  agent any
  stages {
    stage('Linux Build') {
      steps {
        git(poll: true, url: 'https://github.com/PolyMC/PolyMC', branch: 'develop')
      }
    }

  }
}