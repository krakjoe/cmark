--TEST--
CommonMark\Parser Constructor Error
--FILE--
<?php
try {
	$parser = new CommonMark\Parser([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
