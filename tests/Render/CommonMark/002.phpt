--TEST--
CommonMark\Render CommonMark Error
--FILE--
<?php
try {
	CommonMark\Render\CommonMark([]);
} catch (InvalidArgumentException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK

