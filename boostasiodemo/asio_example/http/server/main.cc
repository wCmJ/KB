
#include <iostream>
#include <string>
#include <asio.hpp>
#include "server.h"

int main(int argc, char* argv[])
{
  try
  {
    // Check command line arguments.
    if (argc != 3)
    {
      std::cerr << "Usage: http_server <address> <port>\n";
      return 1;
    }

    // Initialise the server.
    http::server::server s(argv[1], argv[2]);

    // Run the server until stopped.
    s.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "exception: " << e.what() << "\n";
  }

  return 0;
}