properties([parameters([
  booleanParam(defaultValue: true, description: '', name: 'x86_64_linux'),
  booleanParam(defaultValue: false, description: '', name: 'armv7_linux'),
  booleanParam(defaultValue: false, description: '', name: 'armv8_linux'),
  booleanParam(defaultValue: false, description: '', name: 'x86_64_macos'),
  booleanParam(defaultValue: false, description: '', name: 'x86_64_win'),
  booleanParam(defaultValue: false, description: 'Build coverage', name: 'coverage'),
  booleanParam(defaultValue: false, description: 'Merge this PR to target after success build', name: 'merge_pr'),
  booleanParam(defaultValue: false, description: 'Scheduled nightly build', name: 'nightly'),
  choice(choices: 'Debug\nRelease', description: 'Iroha build type', name: 'build_type'),
  booleanParam(defaultValue: false, description: 'Build `bindings`', name: 'bindings'),
  booleanParam(defaultValue: false, description: 'Build Java bindings', name: 'JavaBindings'),
  choice(choices: 'Release\nDebug', description: 'Java bindings build type', name: 'JBBuildType'),
  booleanParam(defaultValue: false, description: 'Build Python bindings', name: 'PythonBindings'),
  choice(choices: 'Release\nDebug', description: 'Python bindings build type', name: 'PBBuildType'),
  choice(choices: 'python3\npython2', description: 'Python bindings version', name: 'PBVersion'),
  booleanParam(defaultValue: false, description: 'Build Android bindings', name: 'AndroidBindings'),
  choice(choices: '26\n25\n24\n23\n22\n21\n20\n19\n18\n17\n16\n15\n14', description: 'Android Bindings ABI Version', name: 'ABABIVersion'),
  choice(choices: 'Release\nDebug', description: 'Android bindings build type', name: 'ABBuildType'),
  choice(choices: 'arm64-v8a\narmeabi-v7a\narmeabi\nx86_64\nx86', description: 'Android bindings platform', name: 'ABPlatform'),
  booleanParam(defaultValue: false, description: 'Build docs', name: 'Doxygen'),
  string(defaultValue: '4', description: 'How much parallelism should we exploit. "4" is optimal for machines with modest amount of memory and at least 4 cores', name: 'PARALLELISM')])])

pipeline {
  environment {
    CCACHE_DIR = '/opt/.ccache'
    CCACHE_RELEASE_DIR = '/opt/.ccache-release'
    SORABOT_TOKEN = credentials('SORABOT_TOKEN')
    SONAR_TOKEN = credentials('SONAR_TOKEN')
    GIT_RAW_BASE_URL = "https://raw.githubusercontent.com/hyperledger/iroha"
    DOCKER_REGISTRY_BASENAME = "hyperledger/iroha"
    JENKINS_DOCKER_IMAGE_DIR = '/tmp/docker'
    GIT_COMMITER_EMAIL = ''

    IROHA_NETWORK = "iroha-0${CHANGE_ID}-${GIT_COMMIT}-${BUILD_NUMBER}"
    IROHA_POSTGRES_HOST = "pg-0${CHANGE_ID}-${GIT_COMMIT}-${BUILD_NUMBER}"
    IROHA_POSTGRES_USER = "pguser${GIT_COMMIT}"
    IROHA_POSTGRES_PASSWORD = "${GIT_COMMIT}"
    IROHA_POSTGRES_PORT = 5432

    DOCKER_AGENT_IMAGE = ''
    DOCKER_IMAGE_FILE = ''
    WORKSPACE_PATH = ''
    MERGE_CONDITIONS_SATISFIED = ''
    REST_PR_CONDITIONS_SATISFIED = ''
    INITIAL_COMMIT_PR = ''
  }

  options {
    buildDiscarder(logRotator(numToKeepStr: '20'))
    timestamps()
  }

  agent any
  stages {
    stage ('Pre-build') {
      agent { label 'master' }
      steps {
        script {
          load ".jenkinsci/enums.groovy"
          def preBuildRoutine = load ".jenkinsci/pre-build.groovy"
          preBuildRoutine.prepare()
          def testSelect = load ".jenkinsci/test-launcher.groovy"
          println testSelect.chooseTestType()
          if (GIT_LOCAL_BRANCH != "develop") {
            def builds = load ".jenkinsci/cancel-builds-same-job.groovy"
            builds.cancelSameJobBuilds()
          }
        }
      }
    }
  }
}
