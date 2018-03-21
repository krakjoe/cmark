--TEST--
CommonMark\Node\CodeBlock write cached
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

try {
	$block->something = "OK";
} catch(RuntimeException $ex) {
	echo "OK";
}

?>
--EXPECT--
OK
