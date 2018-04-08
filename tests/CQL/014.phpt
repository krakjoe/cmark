--TEST--
CommonMark\CQL constraint CodeBlock
--FILE--
<?php
$doc = \CommonMark\Parse(<<<EOD
```
code block
```
EOD
);

$call = new \CommonMark\CQL("/children(CodeBlock)");

$call($doc, function(\CommonMark\Node $root, \CommonMark\Node $node) {
	if ($node instanceof \CommonMark\Node\CodeBlock) {
		echo "OK\n";
	} else  echo "FAIL\n";
});
?>
--EXPECT--
OK

