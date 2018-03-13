--TEST--
CommonMark\Parser Constructor Error
--FILE--
<?php
try {
	$parser = new CommonMark\Parser([]);
} catch (TypeError $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
