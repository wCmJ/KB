Gradle uses plug-ins to extend its core functionality.

A plug-in is an extension to Gradle which typically adds somes preconfigured tasks.

A plug-in is a bundle of logic that can be reused.

A Java plug-in adds tasks to your project.



The usage of Gradle requires an JDK installation.



~/.gradle/gradle.properties contains: org.gradle.daemon=true



1. gradle allows managing the classpath of your projects. it can add JAR files, directories or other projects to the build path of your application.
2. gradle also supports the automatic download of your java library dependencies. specify the dependency in Gradle build file and this triggers Gradle to download the library including its transient dependencies during the build
3. A java library is identified by Gradle via groupId:artifactId:version(GAV in maven)



compile 'org.springframework:spring-web:4.3.10.RELEASE' {

​	exclude group: 'com.google.code.gson', module: 'gson'

}

./gradlew build --info

./gradlew tasks --all



the SourceSets can be used to specify a different project structure. the sources are stored in a src folder rather than in src/main/java.



Evaluate: the progress of build.gradle's running is called evaluate. when is done, the function of afterEvaluate will be invoked.

afterEvaluate{

​	println('after evaluate')//this functioin will be invoked when the endline of build.gradle is executed.

}



Init/configure(run the .gradle)/execute

















