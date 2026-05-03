# Application server in Java - Tomcat/Jetty

## Jetty Explained

Client (Postman/Browser)
↓
Spring Controller (your endpoints)
↓
Spring Service (business logic)
↓
Spring MVC Dispatcher (routing)
↓
[JETTY WEB SERVER] ← Accepts HTTP, manages threads/IO 
↓
OS/Network (TCP sockets)

# Spring Boot + Jetty Error Logging Notes

So when there is logging in the java application there are multiple log entries being made for each error due to this. i searched on the internet what was happening and it lead to this.

## Key Error Logging Insights
- **1 real error, 4 log entries** due to exception bubbling:
  1. Service layer (your structured log - most useful)
  2. Spring MVC (`AbstractHandlerMethodAdapter`)
  3. Jetty server (`Server.handle`)
  4. Servlet wrappers (`HandlerWrapper`)
- **Root cause**: `MandateCancellationFailure: Mandate has IN_PROGRESS presentations`
- **Debug tip**: Focus on structured log with `traceId`, `component`, `msg`. Also other ones have the "err" field and the rool log doesnt have one so you can add the AND NOT "err" to find the one that is the root log skipping the jetty and other logs.
("Failed to cancel mandate for user" and not "err") 

**Jetty role**: HTTP engine that receives requests and calls Spring code

## Spring Boot Server Config

Default: Apache Tomcat
Can swap: Jetty / Undertow (just change dependency)

Maven:

<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-jetty</artifactId>
</dependency>


## Jetty vs Others
| Feature | Jetty | Tomcat | Go net/http |
|---------|--------|--------|-------------|
| Memory | Lightweight ✅ | Standard | Minimal |
| Async | Excellent | Good | Native |
| Config | Dependency swap | Default | Built-in |
| Use case | High concurrency | General | Everything |

## Go vs Java Web Stack

Java: [Business Logic] → [Jetty/Tomcat] → OS
Go: [Business Logic + Server] → OS


**TL;DR**: Jetty = embedded HTTP server for Spring Boot apps. Logs show `org.eclipse.jetty` → your app uses Jetty ✅

