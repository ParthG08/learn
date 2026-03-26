## Overview

# controller 

This is the API Layer. It handles incoming HTTP requests (REST endpoints).

Role: Defines the URL routes (e.g., **/v1/late-fee/calculate**), validates basic input, and returns the final HTTP response (JSON) to the client.


Significance: It’s the "door" through which other services or the mobile app talk to this feature.