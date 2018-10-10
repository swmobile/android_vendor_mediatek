package gov2.nist.javax2.sip.stack;

import gov2.nist.javax2.sip.LogRecord;
import gov2.nist.javax2.sip.LogRecordFactory;

/**
 * The Default Message log factory. This can be replaced as a stack
 * configuration parameter.
 *
 * @author M. Ranganathan
 *
 */
public class DefaultMessageLogFactory implements LogRecordFactory {

    public LogRecord createLogRecord(String message, String source,
            String destination, String timeStamp, boolean isSender,
            String firstLine, String tid, String callId, long tsHeaderValue) {
        return new MessageLog(message, source, destination, timeStamp,
                isSender, firstLine, tid, callId, tsHeaderValue);
    }

    public LogRecord createLogRecord(String message, String source,
            String destination, long timeStamp, boolean isSender,
            String firstLine, String tid, String callId, long timestampVal) {
        return new MessageLog(message, source, destination, timeStamp,
                isSender, firstLine, tid, callId, timestampVal);
    }

}
