--TEST--
CommonMark\Parser Simple
--FILE--
<?php
$doc = CommonMark\Parse(<<<EOD
Title
=====

Paragraph

```fence
code
```
EOD
);

if ($doc->getFirstChild() instanceof CommonMark\Node\Heading) {
	echo "OK";
}
?>
--EXPECT--
OK
