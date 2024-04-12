#include <pistache/http.h>
#include <pistache/endpoint.h>
#include "stock_exchange.h"

using namespace Pistache;

// Define a handler for the HTTP requests
class HelloHandler : public Http::Handler {
public:
    HTTP_PROTOTYPE(HelloHandler)
    void onRequest(const Http::Request&, Http::ResponseWriter writer) override {
        auto orders = DisplayOrders();
        auto mime = MIME(Application, Json);
        // Add CORS headers
        writer.headers()
            .add<Http::Header::AccessControlAllowOrigin>("*") // Allow all origins
            .add<Http::Header::AccessControlAllowMethods>("GET, POST, OPTIONS") // Specify allowed methods
            .add<Http::Header::AccessControlAllowHeaders>("Content-Type"); // Specify allowed headers
        writer.send(Http::Code::Ok, orders.dump(), mime);
    }
};

int main() {
    // Set the address and port for the server
    Pistache::Address addr(Pistache::Ipv4::any(), Pistache::Port(9080));

    // Create the HTTP server
    Http::Endpoint server(addr);
    server.init(Http::Endpoint::options().threads(1));

    // Set the handler and start the server
    server.setHandler(Http::make_handler<HelloHandler>());
    server.serve();

    // Shutdown the server
    server.shutdown();
}
