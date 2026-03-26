#High Level Folder structure of a Spring Project

Typical Java project 

project-root/
│
├── src/
│   ├── main/
│   │   ├── java/        # application code
│   │   └── resources/   # config, properties, yaml
│   │
│   └── test/
│       ├── java/        # unit tests
│       └── resources/
│
├── target/ or build/    # compiled output
├── pom.xml / build.gradle
└── README.md
└── Other config files (Docker, Kubernetes, Maven/Gradle config)

Key points

src/main/java → main code
src/test/java → tests
resources → configs
pom.xml / build.gradle → dependencies