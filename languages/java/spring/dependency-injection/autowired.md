# Dependency Injection

## Overview

This is the urlService that i have injected in the AuthService.java

```java
@Autowired private UrlService urlService;
```

So basically whenever this keyword @Autowired is used spring searches for the injected function in the application context (bucket)

That "bucket" we're referring to is called the **ApplicationContext** (or more broadly, the **Inversion of Control (IoC) Container**).

The Scan: This annotation includes @Autowired, which tells Spring to look through your packages (starting from com.khatabook.loankhata because this is where the class annotated with the @Autowired is located) for any classes marked with:

```java
@Service (like AuthService)
@Component (like TraceIdInterceptor)
@Repository
@Controller / @RestController (like AlertsController)
```

This is what the bucket does

The Bucket: Spring creates one instance (a Singleton) of each of these classes and stores them in the **ApplicationContext**

Wiring: Later, when another class needs one of these services, Spring pulls the instance out of this "bucket" and injects it. For example, in your AppConfig.java, you can see Spring "reaching into the bucket" to grab interceptors using @Autwired

```java
@Autowired TraceIdInterceptor traceIdInterceptor;
@Autowired RoleSecurityContextInterceptor roleSecurityContextInterceptor;
@Autowired IpAddressInterceptor ipAddressInterceptor;
@Autowired UserAgentInterceptor userAgentInterceptor;
@Autowired RequestSourceHeaderInterceptor requestSourceHeaderInterceptor;
@Autowired RequestPlatformHeaderInterceptor requestPlatformHeaderInterceptor;
```


You can also **manually** put things in the bucket using the **@Bean** annotation, like you did for the asyncExecutor in Main.java (lines 46-54).

```java
@Bean
    public Executor asyncExecutor() {
        ThreadPoolTaskExecutor executor = new ContextAwarePoolExecutor();
        executor.setCorePoolSize(8);
        executor.setMaxPoolSize(48);
        executor.setQueueCapacity(2048);
        executor.initialize();
        return executor;
    }
```


(This means that whenever you are injecting the asyncExecutor like this this will call the bean and initialize the executor using that method)

```java
@Service
public class MyService {
    @Autowired
    private Executor asyncExecutor; // This is the Injection!
}
```

Summary
**@Bean**: Defines the object and tells Spring to take care of it.
**The Bean**: Is the actual object (the instance of ThreadPoolTaskExecutor) living inside Spring.
**Injection**: Is the act of Spring handing that object to whatever other class needs it





