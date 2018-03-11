--TEST--
CommonMark\Render Latex Error
--FILE--
<?php
try {
	CommonMark\Render\Latex([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

