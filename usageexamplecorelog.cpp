
CoreLog::initLogger();
CoreLog::info("Application started", CoreLog::CATEGORY_FUNCIOANL, "", CoreLog::SEVERITY_INFORMATION, "Starting services", "None");
CoreLog::error("Database connection failed", CoreLog::CATEGORY_NFUNCIONAL, CoreLog::TYPE_COMMUNICATION, CoreLog::SEVERITY_CRITICAL, "Unable to connect to database", "Retry connection");
