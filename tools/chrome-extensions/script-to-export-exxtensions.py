python3 - <<'PY'
import os, json, csv

base = os.path.expanduser("~/Library/Application Support/Google/Chrome/Default/Extensions")
rows = []

for ext_id in os.listdir(base):
    ext_dir = os.path.join(base, ext_id)
    if not os.path.isdir(ext_dir):
        continue

    versions = sorted(os.listdir(ext_dir), reverse=True)
    for version in versions:
        manifest = os.path.join(ext_dir, version, "manifest.json")
        if os.path.exists(manifest):
            try:
                with open(manifest, "r", encoding="utf-8") as f:
                    data = json.load(f)

                rows.append({
                    "name": data.get("name", ""),
                    "version": data.get("version", ""),
                    "id": ext_id,
                    "webstore_url": f"https://chromewebstore.google.com/detail/{ext_id}"
                })
                break
            except:
                pass

with open("chrome_extensions.csv", "w", newline="", encoding="utf-8") as f:
    writer = csv.DictWriter(f, fieldnames=["name", "version", "id", "webstore_url"])
    writer.writeheader()
    writer.writerows(rows)

print(f"Exported {len(rows)} extensions to chrome_extensions.csv")
