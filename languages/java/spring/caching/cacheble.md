## Cacheble keyword
# Overview


```java
@Cacheable(value = "user_by_id")

public AuthUser getUserFromUserId(String userId) {
    String url = urlService.khatabookBackendGetUserFromUserId();
    url =
            UriComponentsBuilder.fromHttpUrl(url)
                    .queryParam("user_id", userId)
                    .queryParam(
                            Constants.KB_QUERY_PARAM_CLIENT_KEY,
                            Constants.KB_LOANS_SERVICE_TENANT)
                    .toUriString();
    return this.networkService.get(url, getDefaultHeaders(), AuthUser.class, userId);
}
```
**Cache Check**: When you call getUserFromUserId(userId), Spring first looks into a cache named "user_by_id".

**Cache Hit**: If the userId is already in the cache, Spring returns the cached AuthUser object immediately. The method body is not executed, and no network call is made.

**Cache Miss**: If the userId is not in the cache, the method body executes (making a network request via networkService.get).
Populate Cache: After the method successfully returns the AuthUser, Spring automatically stores that result in the "user_by_id" cache using the userId as the key.

Why use it here?

**Performance**: Fetching user data over the network is slow. This makes it near-instant for repeated calls.
**Reduced Load**: It prevents hammering the khatabook-backend service with redundant requests for the same user.






