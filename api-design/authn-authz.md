# Authentication vs. Authorization (and how to do them)

## The core distinction
- **Authentication (AuthN)** — *who are you?* Proving identity (login). → "401 Unauthorized" when it fails.
- **Authorization (AuthZ)** — *what are you allowed to do?* Deciding permissions for an identified user. → "403 Forbidden" when it fails.

AuthN always comes first — you can't authorize an unknown user.

---

## Authentication methods (AuthN)

### 1. API keys
```
Authorization: Bearer sk_live_9f2c...
```
- A long random string identifying the client (usually a machine/service).
- Simple, but **poor for humans**: no per-user identity, easy to leak, hard to revoke selectively.
- Best for: server-to-server, internal tools, machine clients.

### 2. OAuth2 (delegated authorization + identity)
- Lets a user grant a *third-party app* limited access to their data **without sharing the password**.
- Core entities: **Resource Owner** (user), **Client** (the app), **Authorization Server** (e.g. Auth0/Google), **Resource Server** (your API).

#### Main flows
| Flow | Who | Use case |
|---|---|---|
| **Authorization Code** | Web/mobile app, user logs in | Standard for apps with a backend; gets a code → exchanges for tokens |
| **Authorization Code + PKCE** | SPA / mobile (no secure client secret) | Adds a verifier so a leaked code is useless without the PKCE verifier |
| **Client Credentials** | Server-to-server, no user | Machine-to-machine: client gets a token directly with its own credentials |
| **Implicit** (deprecated) | None | Legacy SPA flow — replaced by PKCE, don't use |

#### Authorization Code flow (walk-through)
```
1. App → AuthServer: /authorize?client_id=..&redirect_uri=..&scope=..
2. User logs in + consents
3. AuthServer → browser → redirect to app's redirect_uri with ?code=..
4. App → AuthServer: /token (code + client_secret)   [backend only]
5. AuthServer → app: access_token + refresh_token
6. App → API: Authorization: Bearer <access_token>
```

### 3. JWT (the token format)
A **JSON Web Token** = `header.payload.signature`, base64url-encoded, dot-separated:
```
eyJhbGciOiJIUzI1NiJ9.eyJzdWIiOiIxMjMifQ.sMcxs..
```
- **Header**: algorithm (`alg: HS256` / `RS256`).
- **Payload**: claims — `sub` (subject/user), `exp` (expiry), `iat`, `iss` (issuer), `aud` (audience), custom scopes.
- **Signature**: prevents tampering — verify it before trusting anything.

#### JWT pitfalls
1. **Storage**: localStorage is XSS-readable → prefer httpOnly cookies or in-memory; never log tokens.
2. **Revocation**: a valid JWT can't be invalidated until `exp` (it's stateless) → keep expiries short, or use a blocklist/denylist.
3. **Expiry handling**: clients must refresh (via refresh token) before expiry; silent refresh for UX.
4. **`alg: none` / algorithm confusion attacks** — always verify the signature with a pinned algorithm, and use `RS256` (public/private key) not a shared-secret HS256 for anything public-facing.
5. **Don't trust payload claims without signature verification** (servers must verify, never just base64-decode).
6. **Token size** — keep payload small; JWTs go in headers that can exceed proxy limits.

### Session-based (alternative to tokens)
- Server stores session (DB/Redis) and hands the client a session cookie (opaque id).
- Server-side revocation is trivial (delete the session) → simpler invalidation than JWT.
- Cost: server state per user, session store must scale.
- **Comparison:** session cookies = easy revocation, stateful; JWT = stateless/horizontal-scale friendly, harder revocation. Many systems use a **short-lived JWT + server-side refresh**.

---

## Authorization (AuthZ)

### 1. RBAC (Role-Based Access Control)
- Assign users to **roles**; roles grant **permissions**.
```
user → role (admin, editor, viewer) → permissions (can:edit, can:delete)
```
- Simple, matches org charts; but coarse-grained ("every editor can edit every doc").
- Where: most internal tools and CRUD apps.

### 2. ABAC (Attribute-Based Access Control)
- Decisions from **attributes**: user, resource, action, environment.
- Policy: `allow read file if file.owner == user.id OR user.role == 'admin'`.
- Fine-grained and dynamic (e.g. "only in office hours"), but policy complexity grows fast.

### 3. Scopes (token-level permissions)
- OAuth scopes limit **what a token** may do: `scope: read:orders write:orders`.
- Not about the user — about the *access grant*. Checked by the resource server.

### Common decision: when to allow?
- Always check **AuthZ on every protected endpoint** — don't assume "they got in, so they can do anything."
- **Object-level checks** (ownership) are the classic missed bug:
```js
function canView(user, order) {
  return user.role === 'admin' || order.userId === user.id;
}
```

### Centralized policies
- Frameworks like **Casbin** / **OPA (Open Policy Agent)** / Cedar let you declare policies and evaluate them per-request — good when rules grow beyond simple role checks.

---

## Recommended stack summary
```
AuthN:  OAuth2 (Auth Code + PKCE) → JWT access token (short-lived)
        + refresh token (rotating) for renewal
        + (optional) session cookie for web if you want server-side revocation
AuthZ:  RBAC for coarse roles + object-level ownership checks
        → OPA/Casbin when policy complexity grows
```

---

## Practice ideas
- Run a local Keycloak/Auth0-free flow: implement the Authorization Code flow against GitHub's OAuth or a self-hosted identity server.
- Decode a real JWT (jwt.io) and inspect its claims; tamper with the payload and watch verification fail.
- Build a resource with object-level authz and test: admin can, owner can, stranger → 403.
- Compare session-cookie vs JWT for the same small app and note revocation differences.
