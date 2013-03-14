//
// reply.hpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2012 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef HTTP_SERVER_REPLY_HPP
#define HTTP_SERVER_REPLY_HPP

#ifdef _MSC_VER
#include "targetver.h"
#endif

#include <string>
#include <vector>
#include <json_spirit.h>
#include <boost/asio.hpp>
#include "header.hpp"

namespace http 
{
	namespace server 
	{
		/// A reply to be sent to a client.
		struct reply
		{
		  /// The status of the reply.
		  enum status_type
		  {
			ok = 200,
			created = 201,
			accepted = 202,
			no_content = 204,
			multiple_choices = 300,
			moved_permanently = 301,
			moved_temporarily = 302,
			not_modified = 304,
			bad_request = 400,
			unauthorized = 401,
			forbidden = 403,
			not_found = 404,
			internal_server_error = 500,
			not_implemented = 501,
			bad_gateway = 502,
			service_unavailable = 503
		  } status;

		  /// The headers to be included in the reply.
		  std::vector<header> headers;

		  /// The content to be sent in the reply.
		  std::string content;

		  /// Convert the reply into a vector of buffers. The buffers do not own the
		  /// underlying memory blocks, therefore the reply object must remain valid and
		  /// not be changed until the write operation has completed.
		  std::vector<boost::asio::const_buffer> to_buffers();

		  /// Get a stock reply.
		  static reply stock_reply(status_type status);

		  /// Bad request with some detail supplied. The detail is expected to be already
		  /// html formatted.
		  static reply bad_request_with_detail(const std::string& detail);

		  // Create a json reply
		  static bool reply::create_json_reply(const json_spirit::mValue& value, reply& rep);
		};
	} // namespace server
} // namespace http

#endif // HTTP_SERVER_REPLY_HPP