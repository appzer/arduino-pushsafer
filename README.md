# pushsafer.com-Arduino
Send pushsafer.com messages from the arduino to your Browser, Android, iOS or Windows device.

If you want to use for example a variable in the message, like a temperature reading from a temperature sensor.

Here is an example:

<pre>
Text[40];

Title[19] = "Current Temperature";

char temp_str[8];

// convert float value from temperature sensor to a string, where TemperatureSensor is a variable defined from a temperature sensor value
dtostrf(TemperatureSensor, 4, 1, temp_str);

sprintf(Text,"The current temperature is now %s°",temp_str);

pushsafer(Text,Title,12,3,62,"a");
</pre>