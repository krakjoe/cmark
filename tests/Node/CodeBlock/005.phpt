--TEST--
CommonMark\Node fetch CodeBlock
--FILE--
<?php
$md = <<<MD
```
code
```
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->firstChild instanceof CommonMark\Node\CodeBlock) {
	echo "OK";
}
?>
--EXPECT--
OK
