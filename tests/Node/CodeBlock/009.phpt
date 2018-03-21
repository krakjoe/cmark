--TEST--
CommonMark\Node\CodeBlock write cached
--FILE--
<?php
$block = new CommonMark\Node\CodeBlock;

$f = function() use($block) {
	$block->fence = "fence";
};

$f();
$f();

echo "OK";
?>
--EXPECT--
OK
