--TEST--
CommonMark\Node\CodeBlock fetch Error
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

$child = $doc->firstChild;

try {
	$zero = 0;
	$child->$zero;
} catch(RuntimeException $ex) {
	echo "OK";
}
?>
--EXPECT--
OK
