--TEST--
CommonMark\Render CommonMark Error
--FILE--
<?php
try {
	CommonMark\Render([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

